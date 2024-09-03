class ReviewsController < ApplicationController
  before_action :set_review, only: [:show, :edit, :update, :destroy]

  def show
    @review = Review.find(params[:id])
  end

  def index
    @reviews = Review.all
  end

  
  def new
    @review = Review.new
  end

  def create
    @review = Review.new(review_params)
    @review.user = current_user
  
    if @review.save
      redirect_to reviews_path, notice: 'Review was successfully created.'
    else
      render :new, status: :unprocessable_entity
    end
  end
  

  def edit
    @review = Review.find(params[:id])
  end

  def update
    if @review.update(review_params)
      redirect_to reviews_path, notice: 'Review was successfully updated.'
    else
      render :edit, status: :unprocessable_entity
    end
  end

  def destroy
    @review = Review.find(params[:id])
    @review.destroy
    redirect_to reviews_path, status: :see_other
  end

  private
  def set_review
    @review = Review.find(params[:id])
  rescue ActiveRecord::RecordNotFound
    redirect_to reviews_path, alert: 'Review not found'
  end

  def review_params
    params.require(:review).permit(:actividad_id, :rating, :content)
  end

end
