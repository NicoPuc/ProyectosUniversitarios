class RemoveDescriptionFromReviews < ActiveRecord::Migration[7.0]
  def change
    remove_column :reviews, :descripcion, :text
  end
end
