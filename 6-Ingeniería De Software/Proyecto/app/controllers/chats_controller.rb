class ChatsController < ApplicationController
  before_action :set_chat, only: [:show]

  def index
    @chats = Chat.where(user1: current_user).or(Chat.where(user2: current_user))
    @actividads = Actividad.all
    # actividades sin chat por parte del current_user
    @actividads_without_chat = @actividads.select { |actividad| !Chat.between_users(current_user, actividad.user).any? }
    #actividads_without_chat donde el current_user es el creador de la actividad
    @actividads_without_chat = @actividads_without_chat.select { |actividad| actividad.user != current_user }
  end

  def show
    @chat = Chat.find(params[:id])
    @messages = @chat.messages.order(created_at: :asc)
    @message = Message.new(chat: @chat)
  end

  def create
    actividad_id = params[:chat][:actividad_id]
    user2_id = Actividad.find(actividad_id).user
  
    existing_chat = Chat.between_users(current_user, user2_id).first
    if existing_chat
      redirect_to chat_path(existing_chat)
    else
      @chat = Chat.new(actividad_id: actividad_id, user1: current_user, user2: user2_id)
      if @chat.save
        redirect_to chat_path(@chat)
      else
        flash[:error] = "Hubo un problema al crear el chat. Por favor, inténtalo de nuevo."
        render :new
      end
    end
  end

  def destroy
    @chat = Chat.find(params[:id])
    @chat.destroy
    redirect_to chats_path
  end

  private
  
  def set_chat
    @chat = Chat.find(params[:id])
  end
end