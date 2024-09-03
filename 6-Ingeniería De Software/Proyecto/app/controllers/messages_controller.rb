class MessagesController < ApplicationController
  def create
    @chat = Chat.find(params[:message][:chat_id])
    @message = Message.new(message_params)
    @message.user = current_user

    if @message.save
      redirect_to chat_path(@chat)
    end
  end

  private

  def message_params
    params.require(:message).permit(:content, :chat_id)
  end
end